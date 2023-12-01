<script setup lang="ts">

import { ref, reactive, onMounted,  } from 'vue'
import router from '../router/index'
import axios from 'axios'

var isInProgress = ref(false);

function reboot() {
  isInProgress.value = true;
  axios.get('/api/reboot')
  .then(function (response) {
    // handle success
    console.log(response);
   
      router.push({ path: '/' }); 
  })
  .catch(function (error) {
    // handle error`
    console.log(error);
  })
  .finally(function () {
    // always executed
    isInProgress.value = false;
  });
  
}
</script>

<template>
  <main>
    Please confirm that you want to reboot board?
    <br/>
    <button type="button" class="btn btn-primary mb-5" @click="reboot()" :disabled="isInProgress">Reboot</button>
  </main>
</template>
