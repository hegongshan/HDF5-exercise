#include <hdf5.h>

int main() 
{
    herr_t      status;

    status = H5Fdelete("test.h5", H5P_DEFAULT);
}