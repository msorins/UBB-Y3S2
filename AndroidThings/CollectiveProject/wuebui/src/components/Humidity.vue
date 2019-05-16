<script>
import { Line } from "vue-chartjs";

export default {
  name: "Humidity",
  extends: Line,
  props: {
    humidity: Array,
    labels: Array,
  },
  watch : {
    humidity: function(oldData, newData) {
        this.doRenderChart()
    },
    labels: function(oldData, newData) {
        this.doRenderChart()
    },
  },
  data: function() {
    return {
      MAX_DATA: 60
    };
  },
  mounted() {
    // Make get requests
    // this.$nextTick(function() {
    //   window.setInterval(() => {
    //     this.getData();
    //   }, 1000);
    // });
  },
  methods: {
    getData() {
      this.axios.get("http://192.168.43.130:5000/humidity").then(response => {
        // this.$set(this.$data.humidity, "b", 2);
        // console.log(response.data);

        // this.$data.humidity.push(response.data);
        // if (this.$data.labels.length == 0) {
        //   this.$data.labels.push(0);
        // } else {
        //   this.$data.labels.push(
        //     this.$data.labels[this.$data.labels.length - 1] + 1
        //   );
        // }

        // if(this.$data.humidity.length > this.$data.MAX_DATA) {
        //   this.$data.humidity.shift()
        //   this.$data.labels.shift()
        // }

        // // Render the cart
        // this.doRenderChart()
      });
    },
    doRenderChart() {
      this.renderChart(
          {
            labels: this.$props.labels,
            datasets: [
              {
                label: "Data One",
                backgroundColor: "#009688",
                data: this.$props.humidity
              }
            ]
          },
          {
            responsive: true,
            maintainAspectRatio: false,
            legend: {
              display: false
            },
            animation: {
              duration: 0 // general animation time
            },
            tooltips: {
              callbacks: {
                label: function(tooltipItem) {
                  return tooltipItem.yLabel;
                }
              }
            }
          }
        );
    }
  }
};
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>
h3 {
  margin: 40px 0 0;
}
ul {
  list-style-type: none;
  padding: 0;
}
li {
  display: inline-block;
  margin: 0 10px;
}
a {
  color: #42b983;
}
</style>
