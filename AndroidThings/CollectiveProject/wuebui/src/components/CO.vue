<script>
import { Line } from "vue-chartjs";

export default {
  name: "Temperature",
  extends: Line,
  data: function() {
    return {
      CO: [],
      labels: [],
      MAX_DATA: 60
    };
  },
  mounted() {
    // Make get requests
    this.$nextTick(function() {
      window.setInterval(() => {
        this.getData();
      }, 1000);
    });
  },
  methods: {
    getData() {
      this.axios.get("http://192.168.43.130:5000/co").then(response => {
        this.$set(this.$data.CO, "b", 2);
        console.log(response.data);

        this.$data.CO.push(response.data);
        if (this.$data.labels.length == 0) {
          this.$data.labels.push(0);
        } else {
          this.$data.labels.push(
            this.$data.labels[this.$data.labels.length - 1] + 1
          );
        }

        if(this.$data.CO.length > this.$data.MAX_DATA) {
          this.$data.CO.shift()
          this.$data.labels.shift()
        }

        // Render the cart
        this.renderChart(
          {
            labels: this.$data.labels,
            datasets: [
              {
                label: "Data One",
                backgroundColor: "#009688",
                data: this.$data.CO
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
      });
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
