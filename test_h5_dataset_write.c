#include <hdf5.h>

#define DIM0 4
#define DIM1 6

int main(int argc, char const *argv[])
{
    hid_t file_id, dataspace_id, dataset_id;
    herr_t status;
    int dset_data[DIM0][DIM1];

    // 1.打开文件
    file_id = H5Fopen("test.h5", H5F_ACC_RDWR, H5P_DEFAULT);
    
    // 2.创建dataspace
    hsize_t dims[] = {DIM0, DIM1};
    dataspace_id = H5Screate_simple(2, dims, NULL);

    // 3.创建数据集
    dataset_id = H5Dcreate(file_id, "/dset", H5T_STD_I32LE, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

    // 4.写入数据
    for (int i = 0; i < DIM0; i++) {
        for (int j = 0; j < DIM1; j++) {
            dset_data[i][j] = i * 6 + j + 1;
        }
    }
    status = H5Dwrite(dataset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, dset_data);
    
    // 5.关闭资源
    status = H5Sclose(dataspace_id);
    status = H5Dclose(dataset_id);
    status = H5Fclose(file_id);
    return 0;
}
