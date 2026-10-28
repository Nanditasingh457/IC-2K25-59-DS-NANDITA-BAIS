# Lab 01: Reflections, Learnings & Technical Difficulties

**Course:** IC-307D Data Structures and Algorithms LAB  
**Cluster:** Unit 1 - Introduction to Data Structures & Arrays  
**Author:** Nandita Bais (Roll No: IC-2K25-59)

---

## 1. What I Learned
- **Contiguous Allocation Discipline:** Deepened understanding of memory indexing formulas in 1D and 2D arrays, understanding how compilers translate index notation `arr[i]` into pointer dereferencing `*(arr + i)`.
- **Sparse Matrix Engineering:** Implemented the 3-Tuple representation and observed dramatic memory savings ($> 85\%$) on high-sparsity matrices.
- **Fast Transpose Mastery:** Learned how prefix sums transform quadratic scan patterns into linear time algorithms.

## 2. Difficulties Encountered
- **Buffer Overflow & Input Flushing:** Handling invalid non-numeric inputs in interactive menus caused infinite loops if `stdin` was not cleared properly. Implemented `clearInputBuffer()`.
- **Matrix Dimension Mismatches:** Handled rectangular matrices during multiplication and rotation to prevent array index out-of-bounds crashes.

## 3. Algorithmic Optimizations
- **Reversal Rotation:** Replaced $O(k \cdot n)$ shifting with $O(n)$ in-place 3-step reversal algorithm.
- **Fast Transpose:** Implemented frequency count hashing to achieve $O(cols + non\_zeros)$ time.
