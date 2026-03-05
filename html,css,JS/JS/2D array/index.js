const matrix = [[1, 2, 3],
                [4, 5, 6],
                [7, 8, 9]];

matrix[1][1] = 'x'; // to change array value of an index

for(let row of matrix){
    const rowString = row.join(' ');
    console.log(rowString);
}