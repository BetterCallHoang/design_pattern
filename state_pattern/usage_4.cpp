/*Trường hợp 4: Hành vi thay đổi theo vòng đời object

Ví dụ: DMA Engine

Idle

Configured

Running

Error

Mỗi trạng thái có behavior khác nhau:

start() chỉ hợp lệ khi Configured

stop() chỉ hợp lệ khi Running

reset() hợp lệ khi Error

State Pattern rất phù hợp cho:

Driver

Network protocol

Workflow engine

UI wizard

Game engine*/