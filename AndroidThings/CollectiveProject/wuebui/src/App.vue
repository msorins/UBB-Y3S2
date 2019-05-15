<template>
  <div id="app">
    <h4>Humidity</h4>
    <Humidity/>

    <h4>Temperature</h4>
    <Temperature/>

    <h4>CO</h4>
    <CO/>
    {{ readings }}
  </div>
</template>

<script>
import Humidity from "./components/Humidity.vue";
import Temperature from "./components/Temperature.vue";
import CO from "./components/CO.vue";
import Firebase from "firebase";

var firebaseApp = Firebase.initializeApp({
  apiKey: "AIzaSyCq0F6t5FTJm5Z1ObRzJOqgXk_N2uqHlEg",
  projectId: "officeairquality-51446",
  databaseURL: "https://officeairquality-51446.firebaseio.com"
});
const firestore = firebaseApp.firestore();

export default {
  name: "app",
  components: {
    Humidity,
    Temperature,
    CO
  },
  data() {
    return {
      readings: []
    };
  },
  firestore: function() {
    return {
      persons: firestore.collection("persons")
    };
  },
  mounted() {
    this.$binding("readings", firestore.collection("readings")).then(readings => {
      console.log(readings); 
    });
  }
};
</script>

<style>
#app {
  font-family: "Avenir", Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  margin-top: 60px;
}
</style>
