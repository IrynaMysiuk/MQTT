<script setup lang="ts">
import { RouterLink, RouterView } from 'vue-router'
</script>

<template>
  <div class="d-flex flex-column">
  <header>
    
    <nav class="navbar navbar-expand-lg navbar-dark bg-dark">
      <button class="navbar-toggler" type="button" data-toggle="collapse" 
        data-target="#navbarToggler" 
        aria-controls="navbarToggler" 
        aria-expanded="false" aria-label="Toggle navigation">
        <span class="navbar-toggler-icon"></span>
      </button>
  <a class="navbar-brand" href="#">SmartFloor</a>

  <div class="collapse navbar-collapse" id="navbarToggler">
    <ul class="navbar-nav mr-auto mt-2 mt-lg-0">
      <li class="nav-item">
        <RouterLink to="/" class="nav-link">Home</RouterLink>
      </li>
      <li class="nav-item">
        <RouterLink to="/configure" class="nav-link">Configure</RouterLink>
      </li>
      <li class="nav-item">
        <RouterLink to="/reboot" class="nav-link">Reboot Esp32</RouterLink>
      </li>
      <li class="nav-item">
        <RouterLink to="/about" class="nav-link">About</RouterLink>
      </li>
    </ul>
   
  </div>
    </nav>
  <!---  <div class="wrapper">
  
      <nav>
        <RouterLink to="/">Home</RouterLink>
        <RouterLink to="/config"></RouterLink>
        <RouterLink to="/reboot">Reboot</RouterLink>
        <RouterLink to="/about">About</RouterLink>
      </nav>
    </div>-->
  </header>

  <RouterView />
</div>
</template>

<style scoped>
header {
  line-height: 1.5;
  max-height: 100vh;
}

.logo {
  display: block;
  margin: 0 auto 2rem;
}

nav {
  width: 100%;
  font-size: 12px;
  text-align: center;
  margin-top: 2rem;
}

nav a.router-link-exact-active {
  color: var(--color-text);
}

nav a.router-link-exact-active:hover {
  background-color: transparent;
}

nav a {
  display: inline-block;
  padding: 0 1rem;
  border-left: 1px solid var(--color-border);
}

nav a:first-of-type {
  border: 0;
}

@media (min-width: 1024px) {
  header {
    display: flex;
    place-items: center;
    padding-right: calc(var(--section-gap) / 2);
  }

  .logo {
    margin: 0 2rem 0 0;
  }

  header .wrapper {
    display: flex;
    place-items: flex-start;
    flex-wrap: wrap;
  }

  nav {
    text-align: left;
    margin-left: -1rem;
    font-size: 1rem;

    padding: 1rem 0;
    margin-top: 1rem;
  }
}
</style>
