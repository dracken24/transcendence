// // This is a module can be call by main.ts or others modules

// import { Module } from '@nestjs/common';
// import { AppController } from './app.controller';
// import { AppService } from './app.service';
// import { UserModule } from './user/user.module';
// import { TypeOrmModule } from '@nestjs/typeorm';
// import { User } from './user/user.entity';
// import { SessionEntity } from './user/sessions/session.entity';

// @Module({
// 	imports: [TypeOrmModule.forRoot({
// 		type: 'postgres',
// 		host: 'localhost',
// 		port: 3306, // 3306 home, 5432 school
// 		username: 'postgres',
// 		password: 'Serpents24.',
// 		database: 'brain',
// 		entities: [User, SessionEntity],
// 		synchronize: true, // allow to create or delete table if not exist
// 	}), UserModule], // eventualy take other modules
// 	controllers: [AppController], // take a controler
// 	providers: [AppService], // take a service
// })
// export class AppModule {}

import { Module } from '@nestjs/common';
import { AppController } from './app.controller';
import { AppService } from './app.service';
import { UserModule } from './user/user.module';
import { TypeOrmModule } from '@nestjs/typeorm';
import { User } from './user/user.entity';
import { SessionEntity } from './user/sessions/session.entity';

@Module({
  imports: [
    TypeOrmModule.forRoot({
      type: 'postgres',
      host: 'localhost',
      port: 5432, // Utilisez le port 5432 pour PostgreSQL
      username: 'postgres',
      password: 'Serpents24.',
      database: 'brain',
      entities: [User, SessionEntity], // Ajoutez SessionEntity à la liste des entités
      synchronize: true, // Permet de créer ou supprimer des tables si elles n'existent pas
    }),
    UserModule,
  ],
  controllers: [AppController],
  providers: [AppService],
})
export class AppModule {}
