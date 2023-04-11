import { createRouter, createWebHashHistory } from 'vue-router';

const routes = [
	{ path: '/login', name: 'Login', component: () => import('./components/Login') },
	{ path: '/trade', name: 'Exchange', component: () => import('./components/Trade') },
	{ path: '/admin', name: 'Admin', component: () => import('./components/Admin') }
]
const router = createRouter({
	history: createWebHashHistory(),
	routes
})
router.beforeEach((to)=>{document.title = to.name;})
export default router

