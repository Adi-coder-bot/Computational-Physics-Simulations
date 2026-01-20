document.addEventListener("DOMContentLoaded", () => {
    let anime_id = null;
    let userimg = document.querySelector(".userinfo img");
    let src = userimg?.getAttribute("src");

    if (src === "#") {
        document.getElementsByClassName("form")[0]?.classList.add("act");
        document.getElementById("overlay")?.classList.add("act");
    } else {
        document.getElementsByClassName("form")[0]?.classList.remove("act");
        document.getElementById("overlay")?.classList.remove("act");
    }

    let change = document.querySelector(".change p");
    change?.addEventListener("click", (e) => {
        window.location.href = e.target.dataset.url;
    });

    let lists = document.querySelectorAll("section .list");
    lists.forEach((list) => {
        list.addEventListener("click", () => {
            window.location.href = list.dataset.url;
        });
    });

    let input = document.getElementById("anime_name");
    let suggestiondiv = document.getElementsByClassName("suggestions")[0];
    let form = document.getElementById("searchbar");

    if (input && suggestiondiv && form) {
        input.addEventListener("input", (e) => {
            fetch(`${form.action}?name=${encodeURIComponent(e.target.value)}`)
                .then((response) => response.json())
                .then((data) => {
                    suggestiondiv.classList.add("visible");
                    if (Array.isArray(data.results)) {
                        suggestiondiv.innerHTML = "";
                        data.results.forEach((result) => {
                            suggestiondiv.innerHTML += `<p data-id="${result.id}">${result.name}</p>`;
                        });

                        let choice_anime = document.querySelectorAll(".suggestions p");
                        choice_anime.forEach((ani) => {
                            ani.addEventListener("click", (e) => {
                                input.value = e.target.textContent;
                                anime_id = e.target.dataset.id;
                                suggestiondiv.classList.remove("visible");
                            });
                        });
                    } else if (typeof data.results === "string") {
                        suggestiondiv.innerHTML = `<p>${data.results}</p>`;
                    }
                });
        });

        document.body.addEventListener("click", (e) => {
            if (!(input.contains(e.target) || suggestiondiv.contains(e.target))) {
                suggestiondiv.classList.remove("visible");
            }
        });
    }

    let submit = document.getElementById("hs");
    submit?.addEventListener("click", (e) => {
        e.preventDefault();
        if (anime_id) {
            window.location.href = `/anime/${encodeURIComponent(submit.dataset.email)}/${anime_id}/`;
        }
    });

    let userinfo = document.querySelector(".userinfo .cover");
    let extra = document.querySelector(".extra");
    let overlay = document.getElementById("overlay");

    if (userinfo && extra && overlay) {
        userinfo.addEventListener("click", () => {
            overlay.classList.add("act");
            extra.classList.add("act");
        });

        document.body.addEventListener("click", (e) => {
            if (!(extra.contains(e.target) || userinfo.contains(e.target))) {
                if (extra.classList.contains("act")) {
                    extra.classList.remove("act");
                    overlay.classList.remove("act");
                }
            }
        });
    }

    let logout = document.querySelector("#logout button");
    logout?.addEventListener("click", () => {
        window.location.href = logout.dataset.url;
    });
});