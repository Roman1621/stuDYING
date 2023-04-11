import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { RegisterComponent } from './register/register.component';
import { NewsListComponent } from './news-list/news-list.component';
import { MainPageComponent } from './main-page/main-page.component';
import {LoginComponent} from './login/login.component';

const routes: Routes = [{path: 'login', component: LoginComponent}, {path: 'register', component: RegisterComponent}, {path: 'news', component: NewsListComponent}, {path: 'main_page', component: MainPageComponent}];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
