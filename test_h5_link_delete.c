#include <hdf5.h>

#define DATASET "/dset"
#define GROUP "/MyGroup"

int main(int argc, char const *argv[])
{
    hid_t file_id;
    herr_t status;

    // 1.打开文件
    file_id = H5Fopen("test.h5", H5F_ACC_RDWR, H5P_DEFAULT);

    // 2.删除数据集
    if (H5Lexists(file_id, DATASET, H5P_DEFAULT)) {
        status = H5Ldelete(file_id, DATASET, H5P_DEFAULT);
    }

    // 3.删除组
    if (H5Lexists(file_id, GROUP, H5P_DEFAULT)) {
        status = H5Ldelete(file_id, GROUP, H5P_DEFAULT);
    }

    // 4.关闭并释放资源
    status = H5Fclose(file_id);
    return 0;
}
