#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>

class ModelListener // dây là lớp abstract
{
public:
    ModelListener() : model(0) {}
    
    virtual ~ModelListener() {} // hàm hủy ảo

    void bind(Model* m)
    {
        model = m;
    }
    virtual void updateCurrentScore(int32_t value) {}  // phương thức abstract đươc ghi đè ở Presenter, cầu nối giữa model sang Presenter, từ Presenter sang giao diện.

protected:
    Model* model;
};

#endif // MODELLISTENER_HPP

// CÓ CHỮ VITUARL GIÚP LỚP CON CÓ THẺ OVERRIDE
// ĐA HÌNH LẦ GÌ? 1. ĐA HÌNH TĨNH: là 1 lớp có thể có phương thức trùng tên nhưng khác kiểu dữ liệu,
//                2. ĐA HÌNH ĐỘNG: giúp override ở lớp con
// LỚP ABSTRACT: 1. không thể khởi tạo đối tượng trực tiếp
//               2. có phương thức thuần ảo ( vituarl void draw() = 0 )
//  			 3. có thể có phương thức bình thường


// INTERFACE là lớp chỉ chứa phương thức thuần ảo
// so sánh interface và abstract
/*
 * abstract khi muốn ghi đè 1 số phương thức có đặc tính riêng của từng đối tượng, các phương thức chung vẫn là chung
 * interface đối tượng phải ghi đè tất cả. các đối tượng sử dụng có form giống nhau nhưng nội dung thực hiện khác nhau hoàn toàn.
 * */
