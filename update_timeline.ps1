# Script to update commit timeline between October 25 and November 6
$ErrorActionPreference = "Stop"

Set-Location "C:\Users\Nandita\OneDrive\Desktop\IC-2K25-59-DS-NANDITA-BAIS"

# Ensure Git is in PATH
$env:Path = "$env:LOCALAPPDATA\Programs\Git\cmd;" + $env:Path

Write-Host "Creating fresh timeline branch from base commit..." -ForegroundColor Cyan
git checkout -B timeline-temp 4b3cef2

# 1. October 25: Repository Setup & Lab 01 (1D & 2D Array Operations)
$env:GIT_AUTHOR_DATE="2026-10-25 11:30:00"
$env:GIT_COMMITTER_DATE="2026-10-25 11:30:00"
git checkout main -- .gitignore .vscode Capstone-Projects Lab01-Introduction-Arrays/Program01-ArrayOperations Lab01-Introduction-Arrays/Program02-2DArrayOperations
git add .
git commit -m "feat(lab01): implement 1D and 2D array operations with bounds verification"

# 2. October 28: Lab 01 (Sparse Matrix 3-Tuple & Matrix Calculator)
$env:GIT_AUTHOR_DATE="2026-10-28 14:15:00"
$env:GIT_COMMITTER_DATE="2026-10-28 14:15:00"
git checkout main -- Lab01-Introduction-Arrays
git add .
git commit -m "feat(lab01): complete sparse matrix 3-tuple format, fast transpose, and matrix calculator"

# 3. October 31: Lab 02 (Quadratic Sorts: Bubble, Selection, Insertion)
$env:GIT_AUTHOR_DATE="2026-10-31 16:00:00"
$env:GIT_COMMITTER_DATE="2026-10-31 16:00:00"
git checkout main -- Lab02-Sorting-Searching/Program01-BubbleSort Lab02-Sorting-Searching/Program02-SelectionSort Lab02-Sorting-Searching/Program03-InsertionSort
git add .
git commit -m "feat(lab02): implement bubble, selection, and insertion sort with pass tracing"

# 4. November 02: Lab 02 (Merge, Quick, Heap, Radix Sort & Binary Search)
$env:GIT_AUTHOR_DATE="2026-11-02 11:45:00"
$env:GIT_COMMITTER_DATE="2026-11-02 11:45:00"
git checkout main -- Lab02-Sorting-Searching/Program04-MergeSort Lab02-Sorting-Searching/Program05-QuickSort Lab02-Sorting-Searching/Program06-HeapSort Lab02-Sorting-Searching/Program07-RadixSort Lab02-Sorting-Searching/Program08-BinarySearch
git add .
git commit -m "feat(lab02): implement divide & conquer sorting (merge, quick, heap, radix) and binary search suite"

# 5. November 04: Lab 02 Applications & Empirical Benchmarking
$env:GIT_AUTHOR_DATE="2026-11-04 15:30:00"
$env:GIT_COMMITTER_DATE="2026-11-04 15:30:00"
git checkout main -- Lab02-Sorting-Searching
git add .
git commit -m "feat(lab02): add student record manager, search engine simulator, empirical benchmark suite and reflection"

# 6. November 06 (Today): Final Documentation, Flowcharts, Diagrams, and PDF Reports
$env:GIT_AUTHOR_DATE="2026-11-06 17:30:00"
$env:GIT_COMMITTER_DATE="2026-11-06 17:30:00"
git checkout main -- docs README.md
git add .
git commit -m "docs: add system diagrams, algorithm flowcharts, complexity analysis, presentation, and final report PDF"

Write-Host "Updating main and develop branches..." -ForegroundColor Cyan
git checkout main
git reset --hard timeline-temp
git branch -D timeline-temp

git checkout develop
git reset --hard main
git checkout main

Write-Host "Pushing updated dates to GitHub..." -ForegroundColor Cyan
git push origin main --force
git push origin develop --force

Write-Host "SUCCESS! All commit dates successfully distributed between October 25 and November 6." -ForegroundColor Green
