#include <hdf5.h>

int main() 
{
    hid_t       file_id;
    herr_t      status;

    file_id = H5Fcreate("test.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    status = H5Fclose(file_id);
}