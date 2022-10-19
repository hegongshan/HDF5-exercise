#include <hdf5.h>

#define DIM0 4
#define DIM1 6

int main(int argc, char const *argv[])
{
    hid_t file_id, group_id, dataset_id, space_id;
    herr_t status;
    int dset_data[DIM0][DIM1];

    // 1.打开文件
    file_id = H5Fopen("test.h5", H5F_ACC_RDWR, H5P_DEFAULT);
    
    // 2.创建组
    group_id = H5Gcreate(file_id, "MyGroup", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

    // 3.在组中创建数据集
    hsize_t dims[] = {DIM0, DIM1};
    space_id = H5Screate_simple(2, dims, NULL);
    dataset_id = H5Dcreate(group_id, "DS1", H5T_STD_I32LE, space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    
    // 4.关闭并释放资源
    status = H5Sclose(space_id);
    status = H5Dclose(dataset_id);
    status = H5Gclose(group_id);
    status = H5Fclose(file_id);
    return 0;
}
