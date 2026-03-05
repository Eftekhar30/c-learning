const checkBox = document.getElementById("checkBox");
const visaBtn = document.getElementById("visaBtn");
const MasterCardBtn = document.getElementById("MasterCardBtn");
const PaypalBtn = document.getElementById("PaypalBtn");
const submit = document.getElementById("sub");
const subResult = document.getElementById("subResult");
const paymentResult = document.getElementById("paymentResult");

submit.onclick = function(){
    if(checkBox.checked){
        subResult.textContent = `Thanks for subscribing!`;
        if(visaBtn.checked){
            paymentResult.textContent = `You are paying with VisaCard`;
        } else if(MasterCardBtn.checked){
            paymentResult.textContent = `You are paying with MasterCard.`;
        } else if(PaypalBtn.checked){
            paymentResult.textContent = `You are paying with Paypal.`
        } else{
            paymentResult.textContent = `Payment method is required!`;
        }
    }
    else{
        subResult.textContent = `You are NOT subscribed!`;
        if(visaBtn.checked){
            paymentResult.textContent = `Invalid!`;
        } else if(MasterCardBtn.checked){
            paymentResult.textContent = `Invalid!`;
        } else if(PaypalBtn.checked){
            paymentResult.textContent = `Invalid!`
        }
    }
    
}