import h5py
import numpy as np

with h5py.File('test_chunk.h5', 'w') as file:
    data=np.empty(shape=(6, 8), dtype=np.int32)
    for i in range(6):
        for j in range(8):
            data[i, j] = i * 6 + j + 1

    file.create_dataset('chunked_dset', 
        shape=(6, 8), 
        dtype=h5py.h5t.STD_I32LE, 
        data=data,
        chunks=(4, 4))