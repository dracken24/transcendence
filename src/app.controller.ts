// It's like a router

import { Controller, Get } from '@nestjs/common';
import { AppService } from './app.service';

@Controller()
export class AppController {
  constructor(private readonly appService: AppService) {}

  @Get() //if nothing is in get, default is getHello()
  getHello(): string {
    return this.appService.getHello();
  }
}
