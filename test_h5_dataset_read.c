#include <stdio.h>

#include <hdf5.h>

#define DIM0 4
#define DIM1 6

int main(int argc, char const *argv[])
{
    hid_t file_id, dataset_id;
    herr_t status;
    int dset_data[DIM0][DIM1];

    // 1.打开文件和数据集
    file_id = H5Fopen("test.h5", H5F_ACC_RDONLY, H5P_DEFAULT);
    dataset_id = H5Dopen(file_id, "/dset", H5P_DEFAULT);

    // 2.读取数据集中的数据
    status = H5Dread(dataset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, dset_data);
    for (int i = 0; i < DIM0; i++) {
        printf (" [");
        for (int j = 0; j < DIM1; j++) {
            printf(" %3d", dset_data[i][j]);
        }
        printf ("]\n");
    }
    
    // 3.关闭并释放资源
    status = H5Dclose(dataset_id);
    status = H5Fclose(file_id);
    return 0;
}
