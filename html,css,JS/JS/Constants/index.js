// const PI = 3.14159;
// let radius;
// let circumference;
// radius = window.prompt(`enter the radius of a circle`);
// radius = Number(radius);


// circumference = 2 *pi * radius;

// console.log(circumference);

const PI = 3.14159;
let radius;
let circumference;

document.getElementById("Submit").onclick = function(){
    radius = document.getElementById("text").value;
    radius = Number(radius);
    circumference = 2 * PI * radius;
    document.getElementById("h3").textContent = circumference + `cm`;
}