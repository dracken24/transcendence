// This is a module can be call by main.ts or others modules

import { Module } from '@nestjs/common';
import { AppController } from './app.controller';
import { AppService } from './app.service';
import { UserModule } from './user/user.module';
import { TypeOrmModule } from '@nestjs/typeorm';
import { User } from './user/user.entity';

@Module({
	imports: [TypeOrmModule.forRoot({
		type: 'postgres',
		host: 'localhost',
		port: 3306,
		username: 'postgres',
		password: 'Serpents24.',
		database: 'brain',
		entities: [User],
		synchronize: true, // allow to create or delete table if not exist
	}), UserModule], // eventualy take other modules
	controllers: [AppController], // take a controler
	providers: [AppService], // take a service
})
export class AppModule {}
