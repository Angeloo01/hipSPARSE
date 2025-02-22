/* ************************************************************************
 * Copyright (C) 2020 Advanced Micro Devices, Inc. All rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * ************************************************************************ */

#pragma once
#ifndef TESTING_GEMMI_HPP
#define TESTING_GEMMI_HPP

#include "hipsparse.hpp"
#include "hipsparse_test_unique_ptr.hpp"
#include "unit.hpp"
#include "utility.hpp"

#include <hipsparse.h>
#include <string>

using namespace hipsparse;
using namespace hipsparse_test;

template <typename T>
void testing_gemmi_bad_arg(void)
{
#ifdef __HIP_PLATFORM_NVIDIA__
    // do not test for bad args
    return;
#endif
    int safe_size = 100;
    T   alpha     = 0.6;
    T   beta      = 0.2;

    std::unique_ptr<handle_struct> unique_ptr_handle(new handle_struct);
    hipsparseHandle_t              handle = unique_ptr_handle->handle;

    auto dptr_managed = hipsparse_unique_ptr{device_malloc(sizeof(int) * safe_size), device_free};
    auto drow_managed = hipsparse_unique_ptr{device_malloc(sizeof(int) * safe_size), device_free};
    auto dval_managed = hipsparse_unique_ptr{device_malloc(sizeof(T) * safe_size), device_free};
    auto dA_managed   = hipsparse_unique_ptr{device_malloc(sizeof(T) * safe_size), device_free};
    auto dC_managed   = hipsparse_unique_ptr{device_malloc(sizeof(T) * safe_size), device_free};

    int* dptr = (int*)dptr_managed.get();
    int* drow = (int*)drow_managed.get();
    T*   dval = (T*)dval_managed.get();
    T*   dA   = (T*)dA_managed.get();
    T*   dC   = (T*)dC_managed.get();

    if(!dval || !dptr || !drow || !dA || !dC)
    {
        PRINT_IF_HIP_ERROR(hipErrorOutOfMemory);
        return;
    }

    verify_hipsparse_status_invalid_handle(hipsparseXgemmi<T>(nullptr,
                                                              safe_size,
                                                              safe_size,
                                                              safe_size,
                                                              safe_size,
                                                              &alpha,
                                                              dA,
                                                              safe_size,
                                                              dval,
                                                              dptr,
                                                              drow,
                                                              &beta,
                                                              dC,
                                                              safe_size));
    verify_hipsparse_status_invalid_pointer(hipsparseXgemmi<T>(handle,
                                                               safe_size,
                                                               safe_size,
                                                               safe_size,
                                                               safe_size,
                                                               nullptr,
                                                               dA,
                                                               safe_size,
                                                               dval,
                                                               dptr,
                                                               drow,
                                                               &beta,
                                                               dC,
                                                               safe_size),
                                            "Error: alpha is nullptr");
    verify_hipsparse_status_invalid_pointer(hipsparseXgemmi<T>(handle,
                                                               safe_size,
                                                               safe_size,
                                                               safe_size,
                                                               safe_size,
                                                               &alpha,
                                                               nullptr,
                                                               safe_size,
                                                               dval,
                                                               dptr,
                                                               drow,
                                                               &beta,
                                                               dC,
                                                               safe_size),
                                            "Error: A is nullptr");
    verify_hipsparse_status_invalid_pointer(hipsparseXgemmi<T>(handle,
                                                               safe_size,
                                                               safe_size,
                                                               safe_size,
                                                               safe_size,
                                                               &alpha,
                                                               dA,
                                                               safe_size,
                                                               nullptr,
                                                               dptr,
                                                               drow,
                                                               &beta,
                                                               dC,
                                                               safe_size),
                                            "Error: cscValB is nullptr");
    verify_hipsparse_status_invalid_pointer(hipsparseXgemmi<T>(handle,
                                                               safe_size,
                                                               safe_size,
                                                               safe_size,
                                                               safe_size,
                                                               &alpha,
                                                               dA,
                                                               safe_size,
                                                               dval,
                                                               nullptr,
                                                               drow,
                                                               &beta,
                                                               dC,
                                                               safe_size),
                                            "Error: cscColPtrB is nullptr");
    verify_hipsparse_status_invalid_pointer(hipsparseXgemmi<T>(handle,
                                                               safe_size,
                                                               safe_size,
                                                               safe_size,
                                                               safe_size,
                                                               &alpha,
                                                               dA,
                                                               safe_size,
                                                               dval,
                                                               dptr,
                                                               nullptr,
                                                               &beta,
                                                               dC,
                                                               safe_size),
                                            "Error: cscRowIndB is nullptr");
    verify_hipsparse_status_invalid_pointer(hipsparseXgemmi<T>(handle,
                                                               safe_size,
                                                               safe_size,
                                                               safe_size,
                                                               safe_size,
                                                               &alpha,
                                                               dA,
                                                               safe_size,
                                                               dval,
                                                               dptr,
                                                               drow,
                                                               nullptr,
                                                               dC,
                                                               safe_size),
                                            "Error: beta is nullptr");
    verify_hipsparse_status_invalid_pointer(hipsparseXgemmi<T>(handle,
                                                               safe_size,
                                                               safe_size,
                                                               safe_size,
                                                               safe_size,
                                                               &alpha,
                                                               dA,
                                                               safe_size,
                                                               dval,
                                                               dptr,
                                                               drow,
                                                               &beta,
                                                               nullptr,
                                                               safe_size),
                                            "Error: C is nullptr");
    verify_hipsparse_status_invalid_size(hipsparseXgemmi<T>(handle,
                                                            -1,
                                                            safe_size,
                                                            safe_size,
                                                            safe_size,
                                                            &alpha,
                                                            dA,
                                                            safe_size,
                                                            dval,
                                                            dptr,
                                                            drow,
                                                            &beta,
                                                            dC,
                                                            safe_size),
                                         "Error: m is invalid");
    verify_hipsparse_status_invalid_size(hipsparseXgemmi<T>(handle,
                                                            safe_size,
                                                            -1,
                                                            safe_size,
                                                            safe_size,
                                                            &alpha,
                                                            dA,
                                                            safe_size,
                                                            dval,
                                                            dptr,
                                                            drow,
                                                            &beta,
                                                            dC,
                                                            safe_size),
                                         "Error: n is invalid");
    verify_hipsparse_status_invalid_size(hipsparseXgemmi<T>(handle,
                                                            safe_size,
                                                            safe_size,
                                                            -1,
                                                            safe_size,
                                                            &alpha,
                                                            dA,
                                                            safe_size,
                                                            dval,
                                                            dptr,
                                                            drow,
                                                            &beta,
                                                            dC,
                                                            safe_size),
                                         "Error: k is invalid");
    verify_hipsparse_status_invalid_size(hipsparseXgemmi<T>(handle,
                                                            safe_size,
                                                            safe_size,
                                                            safe_size,
                                                            -1,
                                                            &alpha,
                                                            dA,
                                                            safe_size,
                                                            dval,
                                                            dptr,
                                                            drow,
                                                            &beta,
                                                            dC,
                                                            safe_size),
                                         "Error: nnz is invalid");
    verify_hipsparse_status_invalid_size(hipsparseXgemmi<T>(handle,
                                                            safe_size,
                                                            safe_size,
                                                            safe_size,
                                                            safe_size,
                                                            &alpha,
                                                            dA,
                                                            -1,
                                                            dval,
                                                            dptr,
                                                            drow,
                                                            &beta,
                                                            dC,
                                                            safe_size),
                                         "Error: lda is invalid");
    verify_hipsparse_status_invalid_size(hipsparseXgemmi<T>(handle,
                                                            safe_size,
                                                            safe_size,
                                                            safe_size,
                                                            safe_size,
                                                            &alpha,
                                                            dA,
                                                            safe_size,
                                                            dval,
                                                            dptr,
                                                            drow,
                                                            &beta,
                                                            dC,
                                                            -1),
                                         "Error: ldc is invalid");
}

template <typename T>
hipsparseStatus_t testing_gemmi(Arguments argus)
{
    int               safe_size = 100;
    int               M         = argus.M;
    int               N         = argus.N;
    int               K         = argus.K;
    int               lda       = argus.lda;
    int               ldc       = argus.ldc;
    T                 h_alpha   = make_DataType<T>(argus.alpha);
    T                 h_beta    = make_DataType<T>(argus.beta);
    std::string       binfile   = "";
    std::string       filename  = "";
    hipsparseStatus_t status;

    // When in testing mode, M == N == -99 indicates that we are testing with a real
    // matrix from cise.ufl.edu
    if(K == -99 && N == -99 && argus.timing == 0)
    {
        binfile = argus.filename;
        K = N = safe_size;
    }

    if(argus.timing == 1)
    {
        filename = argus.filename;
    }

    std::unique_ptr<handle_struct> test_handle(new handle_struct);
    hipsparseHandle_t              handle = test_handle->handle;

    // Determine number of non-zero elements
    double scale = 0.02;
    if(K > 1000 || N > 1000)
    {
        scale = 2.0 / std::max(K, N);
    }
    int nnz = K * scale * N;

#ifdef __HIP_PLATFORM_NVIDIA__
    // Do not test args in cusparse
    if(M <= 0 || N <= 0 || K <= 0)
    {
        return HIPSPARSE_STATUS_SUCCESS;
    }
#endif

    // Argument sanity check before allocating invalid memory
    if(M <= 0 || N <= 0 || K < 0)
    {
        auto dptr_managed
            = hipsparse_unique_ptr{device_malloc(sizeof(int) * safe_size), device_free};
        auto drow_managed
            = hipsparse_unique_ptr{device_malloc(sizeof(int) * safe_size), device_free};
        auto dval_managed = hipsparse_unique_ptr{device_malloc(sizeof(T) * safe_size), device_free};
        auto dA_managed   = hipsparse_unique_ptr{device_malloc(sizeof(T) * safe_size), device_free};
        auto dC_managed   = hipsparse_unique_ptr{device_malloc(sizeof(T) * safe_size), device_free};

        int* dptr = (int*)dptr_managed.get();
        int* drow = (int*)drow_managed.get();
        T*   dval = (T*)dval_managed.get();
        T*   dA   = (T*)dA_managed.get();
        T*   dC   = (T*)dC_managed.get();

        if(!dval || !dptr || !drow || !dA || !dC)
        {
            verify_hipsparse_status_success(HIPSPARSE_STATUS_ALLOC_FAILED,
                                            "!dptr || !drow || !dval || !dA || !dC");
            return HIPSPARSE_STATUS_ALLOC_FAILED;
        }

        CHECK_HIPSPARSE_ERROR(hipsparseSetPointerMode(handle, HIPSPARSE_POINTER_MODE_HOST));
        status = hipsparseXgemmi(
            handle, M, N, K, nnz, &h_alpha, dA, lda, dval, dptr, drow, &h_beta, dC, ldc);

        if(M < 0 || N < 0 || K < 0 || nnz < 0)
        {
            verify_hipsparse_status_invalid_size(status,
                                                 "Error: M < 0 || N < 0 || K < 0 || nnz < 0");
        }
        else
        {
            verify_hipsparse_status_success(status, "M >= 0 && N >= 0 && K >= 0 && nnz >= 0");
        }

        return HIPSPARSE_STATUS_SUCCESS;
    }

    // Initialize random seed
    srand(12345ULL);

    // Host structures - CSC matrix A
    std::vector<int> hcsc_col_ptrB;
    std::vector<int> hcsc_row_indB;
    std::vector<T>   hcsc_valB;

    // Initial Data on CPU
    if(binfile != "")
    {
        if(read_bin_matrix(binfile.c_str(),
                           N,
                           K,
                           nnz,
                           hcsc_col_ptrB,
                           hcsc_row_indB,
                           hcsc_valB,
                           HIPSPARSE_INDEX_BASE_ZERO)
           != 0)
        {
            fprintf(stderr, "Cannot open [read] %s\n", binfile.c_str());
            return HIPSPARSE_STATUS_INTERNAL_ERROR;
        }
    }
    else if(argus.laplacian)
    {
        N = K = gen_2d_laplacian(
            argus.laplacian, hcsc_col_ptrB, hcsc_row_indB, hcsc_valB, HIPSPARSE_INDEX_BASE_ZERO);
        nnz = hcsc_col_ptrB[N];
    }
    else
    {
        std::vector<int> hcoo_row_indA;

        if(filename != "")
        {
            if(read_mtx_matrix(filename.c_str(),
                               N,
                               K,
                               nnz,
                               hcoo_row_indA,
                               hcsc_row_indB,
                               hcsc_valB,
                               HIPSPARSE_INDEX_BASE_ZERO)
               != 0)
            {
                fprintf(stderr, "Cannot open [read] %s\n", filename.c_str());
                return HIPSPARSE_STATUS_INTERNAL_ERROR;
            }
        }
        else
        {
            gen_matrix_coo(
                N, K, nnz, hcoo_row_indA, hcsc_row_indB, hcsc_valB, HIPSPARSE_INDEX_BASE_ZERO);
        }

        // Convert COO to CSC
        hcsc_col_ptrB.resize(N + 1, 0);
        for(int i = 0; i < nnz; ++i)
        {
            ++hcsc_col_ptrB[hcoo_row_indA[i] + 1];
        }

        hcsc_col_ptrB[0] = 0;
        for(int i = 0; i < N; ++i)
        {
            hcsc_col_ptrB[i + 1] += hcsc_col_ptrB[i];
        }
    }

    lda = std::max(1, M);
    ldc = std::max(1, M);

    int Annz = lda * K;
    int Cnnz = ldc * N;

    // Host structures - Dense matrix B and C
    std::vector<T> hA(Annz);
    std::vector<T> hC_1(Cnnz);
    std::vector<T> hC_2(Cnnz);
    std::vector<T> hC_gold(Cnnz);

    hipsparseInit<T>(hA, M, K);
    hipsparseInit<T>(hC_gold, M, N);

    // allocate memory on device
    auto dcsc_col_ptrB_managed
        = hipsparse_unique_ptr{device_malloc(sizeof(int) * (N + 1)), device_free};
    auto dcsc_row_indB_managed
        = hipsparse_unique_ptr{device_malloc(sizeof(int) * (nnz + 1)), device_free};
    auto dcsc_valB_managed
        = hipsparse_unique_ptr{device_malloc(sizeof(T) * (nnz + 1)), device_free};
    auto dA_managed      = hipsparse_unique_ptr{device_malloc(sizeof(T) * (Annz + 1)), device_free};
    auto dC_1_managed    = hipsparse_unique_ptr{device_malloc(sizeof(T) * Cnnz), device_free};
    auto dC_2_managed    = hipsparse_unique_ptr{device_malloc(sizeof(T) * Cnnz), device_free};
    auto d_alpha_managed = hipsparse_unique_ptr{device_malloc(sizeof(T)), device_free};
    auto d_beta_managed  = hipsparse_unique_ptr{device_malloc(sizeof(T)), device_free};

    int* dcsc_col_ptrB = (int*)dcsc_col_ptrB_managed.get();
    int* dcsc_row_indB = (int*)dcsc_row_indB_managed.get();
    T*   dcsc_valB     = (T*)dcsc_valB_managed.get();
    T*   dA            = (T*)dA_managed.get();
    T*   dC_1          = (T*)dC_1_managed.get();
    T*   dC_2          = (T*)dC_2_managed.get();
    T*   d_alpha       = (T*)d_alpha_managed.get();
    T*   d_beta        = (T*)d_beta_managed.get();

    if(!dcsc_valB || !dcsc_col_ptrB || !dcsc_row_indB || !dA || !dC_1 || !d_alpha || !d_beta)
    {
        verify_hipsparse_status_success(HIPSPARSE_STATUS_ALLOC_FAILED,
                                        "!dcsc_valB || !dcsc_col_ptrB || !dcsc_row_indB || !dA || "
                                        "!dC_1 || !d_alpha || !d_beta");
        return HIPSPARSE_STATUS_ALLOC_FAILED;
    }

    // copy data from CPU to device
    CHECK_HIP_ERROR(hipMemcpy(
        dcsc_col_ptrB, hcsc_col_ptrB.data(), sizeof(int) * (N + 1), hipMemcpyHostToDevice));
    CHECK_HIP_ERROR(
        hipMemcpy(dcsc_row_indB, hcsc_row_indB.data(), sizeof(int) * nnz, hipMemcpyHostToDevice));
    CHECK_HIP_ERROR(hipMemcpy(dcsc_valB, hcsc_valB.data(), sizeof(T) * nnz, hipMemcpyHostToDevice));
    CHECK_HIP_ERROR(hipMemcpy(dA, hA.data(), sizeof(T) * Annz, hipMemcpyHostToDevice));
    CHECK_HIP_ERROR(hipMemcpy(dC_1, hC_gold.data(), sizeof(T) * Cnnz, hipMemcpyHostToDevice));

    if(argus.unit_check)
    {
        CHECK_HIP_ERROR(hipMemcpy(dC_2, dC_1, sizeof(T) * Cnnz, hipMemcpyDeviceToDevice));
        CHECK_HIP_ERROR(hipMemcpy(d_alpha, &h_alpha, sizeof(T), hipMemcpyHostToDevice));
        CHECK_HIP_ERROR(hipMemcpy(d_beta, &h_beta, sizeof(T), hipMemcpyHostToDevice));

        // ROCSPARSE pointer mode host
        CHECK_HIPSPARSE_ERROR(hipsparseSetPointerMode(handle, HIPSPARSE_POINTER_MODE_HOST));
        CHECK_HIPSPARSE_ERROR(hipsparseXgemmi(handle,
                                              M,
                                              N,
                                              K,
                                              nnz,
                                              &h_alpha,
                                              dA,
                                              lda,
                                              dcsc_valB,
                                              dcsc_col_ptrB,
                                              dcsc_row_indB,
                                              &h_beta,
                                              dC_1,
                                              ldc));

        // ROCSPARSE pointer mode device
        CHECK_HIPSPARSE_ERROR(hipsparseSetPointerMode(handle, HIPSPARSE_POINTER_MODE_DEVICE));
        CHECK_HIPSPARSE_ERROR(hipsparseXgemmi(handle,
                                              M,
                                              N,
                                              K,
                                              nnz,
                                              d_alpha,
                                              dA,
                                              lda,
                                              dcsc_valB,
                                              dcsc_col_ptrB,
                                              dcsc_row_indB,
                                              d_beta,
                                              dC_2,
                                              ldc));

        // copy output from device to CPU
        CHECK_HIP_ERROR(hipMemcpy(hC_1.data(), dC_1, sizeof(T) * Cnnz, hipMemcpyDeviceToHost));
        CHECK_HIP_ERROR(hipMemcpy(hC_2.data(), dC_2, sizeof(T) * Cnnz, hipMemcpyDeviceToHost));

        // CPU
        for(int i = 0; i < M; ++i)
        {
            for(int j = 0; j < N; ++j)
            {
                T sum = make_DataType<T>(0);

                int col_begin = hcsc_col_ptrB[j];
                int col_end   = hcsc_col_ptrB[j + 1];

                for(int k = col_begin; k < col_end; ++k)
                {
                    int row_B = hcsc_row_indB[k];
                    T   val_B = hcsc_valB[k];
                    T   val_A = hA[row_B * lda + i];

                    sum = testing_fma(val_A, val_B, sum);
                }

                hC_gold[j * ldc + i]
                    = testing_fma(h_beta, hC_gold[j * ldc + i], testing_mult(h_alpha, sum));
            }
        }

        unit_check_near(M, N, ldc, hC_gold.data(), hC_1.data());
        unit_check_near(M, N, ldc, hC_gold.data(), hC_2.data());
    }

    return HIPSPARSE_STATUS_SUCCESS;
}

#endif // TESTING_GEMMI_HPP
