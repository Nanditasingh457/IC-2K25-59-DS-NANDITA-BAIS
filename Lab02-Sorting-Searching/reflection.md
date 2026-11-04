# Lab 02: Reflections, Learnings & Technical Difficulties

**Course:** IC-307D Data Structures and Algorithms LAB  
**Cluster:** Unit 2 - Sorting & Searching Algorithms  
**Author:** Nandita Bais (Roll No: IC-2K25-59)

---

## 1. What I Learned
- **Algorithmic Duality:** Quadratic algorithms ($O(n^2)$) are intuitive and memory-compact, but scale poorly. Divide-and-conquer ($O(n \log n)$) algorithms maintain speed at high $N$.
- **Pivot Selection in Quick Sort:** Choosing the first or last element causes degradation to $O(n^2)$ on sorted data. Implementing median-of-three pivot selection prevents this degradation.
- **Stability Matters:** Stable sorting (Merge Sort) is crucial when preserving existing secondary sort orders in complex structs.

## 2. Difficulties Encountered
- **Stack Memory Limits:** Deep recursion in Quick Sort can risk stack overflows on degenerate inputs; solved using tail-call optimization loop structures.
- **Hash Collisions:** Balanced load factors ($\alpha < 0.75$) are critical to maintaining near-$O(1)$ retrieval speeds.

## 3. Optimizations Achieved
- Integrated early termination flag in Bubble Sort ($O(n)$ best case).
- Emancipated Radix Sort from comparisons, achieving linear runtime scaling on fixed-length integer keys.
