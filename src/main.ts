import { NestFactory } from '@nestjs/core';
import { AppModule } from './app.module';
import { join } from 'path';
import { NestExpressApplication } from '@nestjs/platform-express';
import { ValidationPipe } from '@nestjs/common';
import * as session from 'express-session';
import * as PgSession from 'connect-pg-simple';
import { Pool } from 'pg'; // import Pool from pg
declare const module: any;

async function bootstrap() {
  const app = await NestFactory.create<NestExpressApplication>(AppModule);
  app.useGlobalPipes(new ValidationPipe); // use validation pipe for signupDto
  app.setBaseViewsDir(join(__dirname, '..', 'views'));
  app.useStaticAssets(join(__dirname, '..', 'public'));
  app.setViewEngine('ejs');

  const pool = new Pool({
    user: 'postgres',
    host: 'localhost',
    database: 'brain',
    password: 'Serpents24.',
    port: 5432, // 3306 home, 5432 school
  });

  const mySQLStore = PgSession(session);
  const store = new mySQLStore({
    pool: pool,
    tableName: 'session', // Nom de la table où stocker les sessions
  });

  app.use(
    session({
      secret: 'my-secret',
      resave: false,
      saveUninitialized: false,
      store: store,
    }),
  );

  await app.listen(3000);

  if (module.hot) {
    module.hot.accept();
    module.hot.dispose(() => app.close());
  }
}

bootstrap();
