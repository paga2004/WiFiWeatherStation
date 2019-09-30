axios.get('/api/entry')
    .then(function (response) {
        console.log(response);
        let date = new Date(response.data.time * 1000);
        let month = date.getMonth() + 1;
        let day = date.getDate();
        let hour = date.getHours();
        let min = date.getMinutes();


        month = (month < 10 ? "0" : "") + month;
        day = (day < 10 ? "0" : "") + day;
        hour = (hour < 10 ? "0" : "") + hour;
        min = (min < 10 ? "0" : "") + min;


        let str = day + "." + month + "." + date.getFullYear() + " " + hour + ":" + min;

        document.getElementById("time").innerHTML = str;
        document.getElementById("temp").innerHTML = response.data.temp + "°C";
        document.getElementById("humidity").innerHTML = response.data.humidity + "%";
    })
    .catch(function (error) {
        // handle error
        console.log(error);
    });


