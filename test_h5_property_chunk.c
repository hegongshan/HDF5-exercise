#include <hdf5.h>

#define DATASET "chunked_dset"
#define DIM0 6
#define DIM1 8
#define CHUNK0 4
#define CHUNK1 4

int main(int argc, char const *argv[])
{
    hid_t file_id, space_id, dcpl_id, dataset_id;
    hsize_t dims[2] = {DIM0, DIM1}; 
    hsize_t chunk[2] = {CHUNK0, CHUNK1};
    int dset_data[DIM0][DIM1];
    herr_t status;
    
    // 1.创建文件
    file_id = H5Fcreate("test_chunk.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

    // 2.创建数据空间
    dims[0] = DIM0;
    dims[1] = DIM1;
    space_id = H5Screate_simple(2, dims, NULL);

    // 3.创建数据集创建属性列表，并设置分块大小
    dcpl_id = H5Pcreate(H5P_DATASET_CREATE);
    status = H5Pset_chunk(dcpl_id, 2, chunk);

    // 4.创建数据集
    dataset_id = H5Dcreate(file_id, DATASET, H5T_STD_I32LE, space_id, H5P_DEFAULT, dcpl_id, H5P_DEFAULT);

    // 5.写入数据
    for (int i = 0; i < DIM0; i++) {
        for (int j = 0; j < DIM1; j++) {
            dset_data[i][j] = i * DIM1 + j + 1;
        }
    }
    status = H5Dwrite(dataset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, dset_data);

    // 6.关闭并释放资源
    status = H5Dclose(dataset_id);
    status = H5Pclose(dcpl_id);
    status = H5Sclose(space_id);
    status = H5Fclose(file_id);
    return 0;
}
