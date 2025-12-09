#include <stdio.h>
#include <lapacke.h>

int main() {
    int n = 3;
    int nrhs = 1;
    int lda = 3;
    int ldb = 3;

    double A[9] = { 1.0, -1.0, 1.0,
                    2.0,  1.0, 3.0,
                    1.0,  1.0, 2.0 };

    double B[3] = { 6.0, 4.0, 5.0 };

    int ipiv[3]; // Pivot indices

    // Call LAPACKE_dgesv to solve the system
    int info = LAPACKE_dgesv(LAPACK_ROW_MAJOR, n, nrhs, A, lda, ipiv, B, ldb);

    if (info == 0) {
        // Print the solution vector (B now holds the solution)
        printf("Solution: ");
        for (int i = 0; i < n; i++) {
            printf("%lf ", B[i]);
        }
        printf("\n");
    } else {
        printf("The computation failed with error code %d\n", info);
    }

    return 0;
}
