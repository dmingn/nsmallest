import numpy as np
import nsmallest
import pytest

n = 10 ** 6
k = 10


@pytest.mark.parametrize(
    'dtype', [
        np.int8,
        np.int16,
        np.int32,
        np.int64,
        np.uint8,
        np.uint16,
        np.uint32,
        np.uint64
    ]
)
def test_int(dtype):
    iinfo = np.iinfo(dtype)
    low = iinfo.min
    high = iinfo.max
    a = np.random.randint(low, high, n, dtype)

    val_np = np.sort(a)[:k]
    val_ns = nsmallest.nsmallest(a, k)

    arg_np = np.argsort(a)[:k]
    arg_ns = nsmallest.argnsmallest(a, k)

    assert val_ns.dtype == dtype

    assert all(val_np == val_ns)
    assert all(a[arg_np] == a[arg_ns])


@pytest.mark.parametrize(
    'dtype', [
        np.float32,
        np.float64
    ]
)
def test_float(dtype):
    a = np.random.rand(n).astype(dtype)

    val_np = np.sort(a)[:k]
    val_ns = nsmallest.nsmallest(a, k)

    arg_np = np.argsort(a)[:k]
    arg_ns = nsmallest.argnsmallest(a, k)

    assert val_ns.dtype == dtype

    assert all(val_np == val_ns)
    assert all(a[arg_np] == a[arg_ns])
