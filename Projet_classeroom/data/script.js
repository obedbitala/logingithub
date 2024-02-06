function validateForm() {
  var x = document.forms["myForm"]["username"].value;
  var y = document.forms["myForm"]["password"].value;
  if (x == "" || y == "") {
    alert("Les champs doivent être remplis");
    return false;
  }
  else if (x == "user1" && y == "password1") {
    alert("Bienvenue, utilisateur 1!");
    window.location.href = "index2.html";
    return true;
    document.getElementById("myForm").reset();
  }
  else if (x == "user2" && y == "password2") {
    alert("Bienvenue, utilisateur 2!");
    window.location.href = "https://www.example.com/page2.html";
    return true;
    document.getElementById("myForm").reset();
  }
  else {
    alert("Nom d'utilisateur ou mot de passe incorrect");
    document.getElementById("myForm").reset();
    return false;
  }
}

// Gestion de RFID 
setInterval(function getData()
{
var xhttp = new XMLHttpRequest();

xhttp.onreadystatechange = function()
{
    if(this.readyState == 4 && this.status == 200)
    {
        document.getElementById("person").innerHTML = this.responseText;
    }
};
xhttp.open("GET", "lireRFID", true);
xhttp.send();
}, 1000);
