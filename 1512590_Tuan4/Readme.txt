TRẦN TRUNG TRẠNG - 1512590
BÀI TẬP TUẦN 4 - File Explorer sử dụng TreeView & ListView
----------------------------------------------
Chức năng đã làm được:
	1. Tạo ra TreeView bên trái, ListView bên phải.

	2. Xét TreeView
		1.Tạo node root là This PC
		2.Lấy danh sách các ổ đĩa trong máy
		3. Bắt sự kiện Expanding, lấy ra đường dẫn dấu ở PARAM để biết mình phải xư lí thư mục nào

	3. Xét ListView
		1.Hiển thị toàn bộ thư mục và tập tin tương ứng với một đường dẫn
		2.Bấm đôi vào một thư mục sẽ thấy toàn bộ thư mục con và tập tin
		3.Tạo ra ListView có 4 cột:
			Ứng với các ổ đĩa: Tên, Loại, Tổng dung lượng, Dung lượng Trống
			Ứng với các tập tin :Tên, Kích thước,Loại tập tin và Ngày chỉnh sửa
		4.Đã dùng icon hệ thống
		5.Bấm đôi vào tập tin sẽ chạy app tương ứng

Các luồng sự kiện:
	 1. Chạy chương trình lên, hiển thị node This PC trên TreeView bên trái ở trạng thái collapse (thu gọn). Bấm vào sẽ xổ xuống các node con là danh sách ổ đĩa.
	 2. Bấm vào ổ đĩa C đang ở trạng thái collapse(thu gọn) trong TreeView bên trái sẽ xổ xuống danh sách các thư mục con.

	
link : https://bitbucket.org/trantrungtrang/windev/commits/f030f06217e53440edab4db64da72205f17a7166
link youtube: https://youtu.be/uHRKG88NIF0