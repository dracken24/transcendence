// SessionEntity.ts

import { Entity, Column, PrimaryGeneratedColumn } from 'typeorm';

@Entity({ name: 'session' })
export class SessionEntity {
  @PrimaryGeneratedColumn()
  id: number;

  // @Column({ name: 'session_id', type: 'varchar', length: 255 })
  // sessionId: string;

  @Column({ name: 'sess', type: 'json' })
  session: any; 
  
  @Column({ name: 'sid', type: 'varchar', length: 255 })
  sid: string;

  // @Column({ name: 'expiresAt', type: 'timestamp' })
  // expiresAt: Date;

  @Column({ name: 'expire', type: 'timestamp' })
  expire: Date;
}