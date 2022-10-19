#include <stdio.h>
#include <assert.h>
#include <hdf5.h>

herr_t print_dataset(hid_t loc_id, const char *name) 
{    
    int rank;
    hid_t space_id, dataset_id;

    dataset_id = H5Dopen(loc_id, name, H5P_DEFAULT);
    space_id = H5Dget_space(dataset_id);
    rank = H5Sget_simple_extent_ndims(space_id);

    hsize_t dims[rank];
    assert(H5Sget_simple_extent_dims(space_id, dims, NULL) == rank);
    for (int i = 0; i < rank; i++) {
        if (i > 0) {
            printf(" ");
        }
        printf("%lld", dims[i]);
        if (i < rank - 1) {
            printf(",");
        }
    }
    H5Sclose(space_id);
    H5Dclose(dataset_id);
}

herr_t op_func(hid_t obj_id, const char *name, const H5O_info_t *info, void *op_data)
{
    printf("/");
    switch(info->type) {
        case H5O_TYPE_GROUP:
            printf ("%s Group\n", name);
            break;
        case H5O_TYPE_DATASET:
            printf ("%s Dataset {", name);
            print_dataset(obj_id, name);
            printf("}\n");
            break;
        default:
            printf ("%s others\n", name);
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    hid_t file_id, group_id;
    herr_t status;

    // 1.打开文件
    file_id = H5Fopen("test.h5", H5F_ACC_RDONLY, H5P_DEFAULT);
    
    // 2.打开组
    group_id = H5Gopen(file_id, "/", H5P_DEFAULT);

    // 3.递归遍历组
    status = H5Ovisit(group_id, H5_INDEX_NAME, H5_ITER_INC, op_func, NULL, H5O_INFO_BASIC);
    
    // 4.关闭并释放资源
    status = H5Gclose(group_id);
    status = H5Fclose(file_id);
    return 0;
}
