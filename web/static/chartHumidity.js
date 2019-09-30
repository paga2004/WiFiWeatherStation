let labels = [], humidity = [];

Chart.defaults.global.hover.mode = 'nearest';

window.onload = function () {
    let ctx = document.getElementById("line-chartcanvas")

    axios.get('/api/entries')
        .then(function (response) {
            console.log(response);
            for (let i = 0; i < response.data.length; i++) {
                let date = new Date(response.data[i].time * 1000);
                let month = date.getMonth() + 1;
                let day = date.getDate();
                let hour = date.getHours();
                let min = date.getMinutes();
                

                month = (month < 10 ? "0" : "") + month;
                day = (day < 10 ? "0" : "") + day;
                hour = (hour < 10 ? "0" : "") + hour;
                min = (min < 10 ? "0" : "") + min;
                

                let str = date.getFullYear() + "-" + month + "-" + day + " " + hour + ":" + min;

                labels.push(str);


                if (response.data[i].humidity > 0) {
                    humidity.push(response.data[i].humidity);
                } else {
                    humidity.push(undefined);
                }

            }


            let options = {
                responsive: true,
                title: {
                    display: true,
                    position: "top",
                    text: "Humidity [%]",
                    fontSize: 24,
                    fontColor: "white"
                },
                
                legend: {
                    display: false
                },
                scales: {
                    yAxes: [{
                        ticks: {
                            fontColor: "black",
                        }
                    }],
                    xAxes: [{
                        ticks: {
                            fontColor: "black",
                        }
                    }]
                }
                
            };
            //line chart data
            let data = {
                labels: labels,
                datasets: [
                    {
                        label: "Humidity [%]",
                        data: humidity,
                        backgroundColor: "grey",
                        borderColor: "white",
                        fill: false,
                        lineTension: 0,
                        pointRadius: 0
                    }
                ]
            };
            let chart = new Chart(ctx, {
                type: "line",
                data: data,
                options: options
            });

        })
        .catch(function (error) {
            // handle error
            console.log(error);
        });


    console.log("bh");
}


