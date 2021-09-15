# sudoku-solver

## General Notes
- This repository contains code that solves sudoku puzzles
- This solver is a work in progress
- The solver can solve simple sudokus in a matter of seconds
- The solver cannot solve harder sudokus due to the complexity of logic required

## Usage Instructions
- Run the C++ file
- Enter the length of the sudoku
  - This must be a perfect square like 9 or 16
- Enter the sudoku grid
  - Separate each value with a space and separate each line with the enter key
  - For unknown values, enter the value 0
  - For values greater than 9, use the associated character
    - Use 'A' or 'a' for 10
    - Use 'B' or 'b' for 11
    - And so on
  - When all data has been entered (defined as length^2 values), press enter
  - The solver will then attempt to solve the given sudoku
    - If the process is successful, the completed sudoku will be printed along with a success message
    - If the process is not successful, a failure message will be displayed along with whatever numbers the sudoku was able to fill in
