#include <hdf5.h>

int main(int argc, char const *argv[])
{
    hid_t file_id, group_id, dataset_id, attr_space_id, attr_id;
    herr_t status;
    hsize_t dims;
    int attr_data[2];

    // 1.打开文件、组和数据集
    file_id = H5Fopen("test.h5", H5F_ACC_RDWR, H5P_DEFAULT);
    group_id = H5Gopen(file_id, "MyGroup", H5P_DEFAULT);
    dataset_id = H5Dopen(group_id, "DS1", H5P_DEFAULT);

    // 2.创建数据集属性
    if (!H5Aexists(dataset_id, "Units")) {
        dims = 2;
        attr_data[0] = 100;
        attr_data[1] = 200;
        attr_space_id = H5Screate_simple(1, &dims, NULL);
        attr_id = H5Acreate(dataset_id, "Units", H5T_STD_I32LE, attr_space_id, H5P_DEFAULT, H5P_DEFAULT);

        // 3.写属性数据
        status = H5Awrite(attr_id, H5T_NATIVE_INT, attr_data);
        
        // 4.关闭并释放资源
        status = H5Aclose(attr_id);
        status = H5Sclose(attr_space_id);
    }
    
    // 4.关闭并释放资源
    status = H5Dclose(dataset_id);
    status = H5Gclose(group_id);
    status = H5Fclose(file_id);
    return 0;
}
