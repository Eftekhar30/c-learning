//easy way = window prompt

// let username;
// username = window.prompt(`whats your username: `);

// console.log(username);


//professional way = html text box

let username;

document.getElementById(`mySubmit`).onclick = function(){
    username = document.getElementById(`mytext`).value;
    document.getElementById(`myH1`).textContent = `hello ${username}`
}