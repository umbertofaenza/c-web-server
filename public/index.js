document.addEventListener('DOMContentLoaded', function() {
    const body = document.querySelector("body");
    const modeBtn = document.querySelector(".mode-switch");

    modeBtn.addEventListener("click", function() {
        let bodyMode = body.classList.value;
        switch (bodyMode) {
            case "dark-mode":
                body.classList.remove("dark-mode");
                body.classList.add("light-mode");

                modeBtn.classList.remove("btn-dark-mode");
                modeBtn.classList.add("btn-light-mode");
                modeBtn.innerHTML = "Switch to Dark Mode";
                break;
            case "light-mode":
                body.classList.remove("light-mode");
                body.classList.add("dark-mode");
                
                modeBtn.classList.remove("btn-light-mode");
                modeBtn.classList.add("btn-dark-mode");
                modeBtn.innerHTML = "Switch to Light Mode";
                break;
            default:
                break;
        }
    })
})
