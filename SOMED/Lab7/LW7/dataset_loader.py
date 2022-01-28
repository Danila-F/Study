# %%
import numpy as np

# %%
def get_dataset(set_name):
    import scipy.io

    m = scipy.io.loadmat('data.mat')
    data_set = m['data'][set_name][0][0]['inputs'][0][0]
    labels = m['data'][set_name][0][0]['targets'][0][0]
    return data_set, labels

# %%
test_x, test_t = get_dataset('test')
training_x, training_t = get_dataset('training')
