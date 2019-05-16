import Vue from 'vue'
import App from './App.vue'
import VueAxios from 'vue-axios'
import axios from 'axios'
import VueFirestore from 'vue-firestore'

require('firebase/firestore')
Vue.config.productionTip = false
Vue.use(VueFirestore)
Vue.use(VueAxios, axios)
Vue.use(require('vue-moment'));

new Vue({
  render: h => h(App),
}).$mount('#app')