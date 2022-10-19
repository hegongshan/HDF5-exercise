#include <hdf5.h>

int main(int argc, char const *argv[])
{
    hid_t file_id, dataset_id;
    herr_t status;

    // 1.打开文件和数据集
    file_id = H5Fopen("test.h5", H5F_ACC_RDWR, H5P_DEFAULT);
    dataset_id = H5Dopen(file_id, "/MyGroup/DS1", H5P_DEFAULT);

    // 2.删除属性
    status = H5Adelete(dataset_id, "Units");
    
    // 3.关闭并释放资源
    status = H5Dclose(dataset_id);
    status = H5Fclose(file_id);
    return 0;
}