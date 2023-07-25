import { Injectable, ConflictException, NotFoundException, UnauthorizedException } from '@nestjs/common';
import { SignupDto } from './dto/signupDto';
import { InjectRepository } from '@nestjs/typeorm';
import { User } from './user.entity';
import { Repository } from 'typeorm';
import * as bcrypt from 'bcrypt';
import { LoginDto } from './dto/loginDto';

@Injectable()
export class UserService {
	constructor(
		@InjectRepository(User)
		private readonly usersRepository: Repository<User>,
	) {}
	
	async postSignup(body: SignupDto): Promise<string> {
		try {
			const { password } = body;
			const hash = await bcrypt.hash(password, 10);
			const user = this.usersRepository.create({... body, password : hash});
			await this.usersRepository.save(user);
			return "User created";
		} catch (error) {
			throw new ConflictException(error.message);
		}
	}

	async postLogin(body: LoginDto) {
        const { password, username } = body;
		const user = await this.usersRepository.findOne({ where : { username : username}});
		if (!user) throw new NotFoundException("User not found");
		const match = await bcrypt.compare(password, user.password);
		if (!match) throw  new UnauthorizedException("Invalid Password");
		return user;
    }
}
