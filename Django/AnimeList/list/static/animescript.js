document.addEventListener("DOMContentLoaded", ()=>{
    let submit = document.querySelector(".down button");
    submit.addEventListener("click", ()=>{
        window.location.href = submit.dataset.url
    });

    document.querySelectorAll("input[name='status']").forEach((input)=>{
        input.addEventListener("change", (e)=>{
            let form = document.querySelector(".status form");
            let csrftoken = document.querySelector(".status form input[name='csrfmiddlewaretoken']").value;
            fetch(
                form.action,
                {
                    method:"POST",
                    body: new FormData(form),
                    headers:{
                        "X-CSRFToken":csrftoken
                    }
                }
            )
            .then(response => response.json())
            .then(data => {
                if (data.success === true){
                    alert("status changed successfully!");
                    let show = document.querySelector(".status p");
                    show.textContent = data.status;
                }
                else{
                    alert("Something went wrong.");
                }
            })

        });
    });
});