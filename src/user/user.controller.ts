import { Controller, Get, Render, Post, Body, Redirect, UseInterceptors, ClassSerializerInterceptor } from '@nestjs/common';
import { SignupDto } from './dto/signupDto';
import { UserService } from './user.service';
import { LoginDto } from './dto/loginDto';

@Controller('user')
export class UserController {
    constructor(private readonly userService : UserService) { }

    @Get("/signup")
    @Render("user/signup")
    getSignup() { }

    @Get("/login")
    @Render("user/login")
    getLogin() { }

    @Post("/signup")
    @Redirect("/user/login")
    async postSignup(@Body() body : SignupDto) {
        return { message : await this.userService.postSignup(body) };
    }

    @UseInterceptors(ClassSerializerInterceptor)
    @Post("/login")
    async postLogin(@Body() body: LoginDto) {
        return await this.userService.postLogin(body);
    }
}
