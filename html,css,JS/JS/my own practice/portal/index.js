const submit = document.getElementById("submit");
const username = document.getElementById("username");
const output = document.getElementById("ouput");

submit.onclick = function() {
    if (username.value.trim() === "") {
        output.textContent = "invalid";
    } else {
        output.textContent = "valid";
    }
}