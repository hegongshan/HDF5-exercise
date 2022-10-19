#include <hdf5.h>

#define DIM 2

int main(int argc, char const *argv[])
{
    hid_t file_id, dataset_id, attr_id, attr_space_id;
    herr_t status;
    int rank, attr_data[DIM];
    hsize_t dims;
    H5S_class_t space_type;

    // 1.打开文件、数据集以及属性
    file_id = H5Fopen("test.h5", H5F_ACC_RDWR, H5P_DEFAULT);
    dataset_id = H5Dopen(file_id, "/MyGroup/DS1", H5P_DEFAULT);
    if(!H5Aexists(dataset_id, "Units")) {
        return 0;
    }
    attr_id = H5Aopen(dataset_id, "Units", H5P_DEFAULT);

    // 2.读取属性
    status = H5Aread(attr_id, H5T_NATIVE_INT, attr_data);
    for (int i = 0; i < DIM; i++) {
        printf("%d\n", attr_data[i]);
    }

    // 3.读取属性的数据空间
    attr_space_id = H5Aget_space(attr_id);
    rank = H5Sget_simple_extent_dims(attr_space_id, &dims, NULL);
    space_type = H5Sget_simple_extent_type(attr_space_id);
    printf("Rank = %d, Dims = %lld, Type of Dataspace (1 denotes simple dataset) = %d\n", rank, dims, space_type);

    // 4.关闭并释放资源
    status = H5Sclose(attr_space_id);
    status = H5Aclose(attr_id);
    status = H5Dclose(dataset_id);
    status = H5Fclose(file_id);
    return 0;
}