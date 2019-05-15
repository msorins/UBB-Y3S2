<template>
  <div id="app">
    <h4> Humidity </h4>
    <Humidity/>

    <h4> Temperature </h4>
    <Temperature/>

    <h4> CO </h4>
    <CO/>
  </div>
</template>

<script>
import Humidity from './components/Humidity.vue'
import Temperature from './components/Temperature.vue'
import CO from './components/CO.vue'

export default {
  name: 'app',
  components: {
    Humidity,
    Temperature,
    CO
  }
}
</script>

<style>
#app {
  font-family: 'Avenir', Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  margin-top: 60px;
}
</style>
