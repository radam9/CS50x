$(".dropdown-menu").on("click", "button", function(event){
    var x = event.currentTarget.innerHTML;
    var y = document.getElementById("navbar");
    if (x == "Dark") {z = "bg-dark"}
    else if (x == "Blue") {z = "bg-primary"}
    else if (x == "Gray") {z = "bg-secondary"}
    else if (x == "Green") {z = "bg-success"}
    else {z = "bg-warning"}

    y.classList.remove(y.classList[3]);
    y.classList.add(z);
})