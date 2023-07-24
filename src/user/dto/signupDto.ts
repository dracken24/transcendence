import { IsString, IsNotEmpty, IsEmail, Length } from 'class-validator';

export class SignupDto {

	@IsString()
	@IsNotEmpty()
	@Length(4, 20)
	readonly username : string;

	@IsString()
	@IsNotEmpty()
	@IsEmail()
	readonly email : string;

	@IsString()
	@IsNotEmpty()
	@Length(8, 30)
	readonly password : string;
}
