# SE DUYÊN 4.0

1. **Giới thiệu:**
   SE DUYÊN 4.0 là chương trình C mô phỏng hệ thống ghép đôi dựa trên ngày sinh, sử dụng hai danh sách liên kết đơn để quản lý người dùng và kết quả tương hợp. Dự án nhằm rèn luyện kỹ năng lập trình cấu trúc, quản lý bộ nhớ động, chia module và thao tác file.

2. **Công nghệ sử dụng:**
   - Ngôn ngữ C
   - Hai danh sách liên kết đơn: `Node` (người dùng) và `ResultNode` (kết quả ghép đôi)
   - Con trỏ và bộ nhớ động
   - Xử lý tệp tin

3. **Yêu cầu kỹ thuật:**
   - Tối thiểu 4 hàm/module độc lập, có hàm trả về giá trị và dùng con trỏ
   - Sử dụng malloc, calloc, free để quản lý bộ nhớ
   - Danh sách liên kết đơn làm cấu trúc chính
   - Đọc/ghi file tự động khi chạy và thoát chương trình
   - Kiểm soát lỗi nhập liệu, dùng #define, tách file .c và .h

4. **Chức năng chính:**
   - Menu điều hướng chương trình
   - Quản lý người dùng: thêm, xóa, sửa, tìm kiếm, hiển thị danh sách
   - **Tính tương hợp:** ghép đôi dựa trên ngày sinh và lưu kết quả
   - Xem lại và dọn dẹp danh sách kết quả ghép đôi
   - Tự động tải dữ liệu từ `data.txt` và `people.txt` khi khởi động
   - Tự động lưu toàn bộ dữ liệu và kết quả vào file khi thoát
   - Chia chương trình thành nhiều module (`list.c`, `seduyen.c`, `Main.c`)
   
