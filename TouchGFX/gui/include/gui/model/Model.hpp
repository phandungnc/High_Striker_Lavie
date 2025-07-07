#ifndef MODEL_HPP
#define MODEL_HPP

#include <cstdint>  // Đảm bảo bao gồm để sử dụng int32_t

class ModelListener;  // Khai báo trước tên lớp ModelListener vì nó sẽ được dùng trong Model.
					  // Giúp tránh việc phải include nguyên file header của ModelListener, làm giảm sự phụ thuộc và thời gian biên dịch.



class Model
{
public:
    Model(); // khởi tạo

    void bind(ModelListener* listener) // Gắn đối tượng ModelListener vào lớp Model.
    								   //Điều này cho phép Model gọi lại các phương thức từ lớp khác (thường là Presenter trong TouchGFX).
    {
        modelListener = listener;
    }

    void tick(); //Thường được gọi liên tục trong mỗi chu kỳ thời gian (tick) của ứng dụng.
				 // Mục đích là để kiểm tra nếu có dữ liệu mới (hasNewScore == true) thì thông báo cho ModelListener.
				 // Hàm tick() thường sẽ được định nghĩa trong model.cpp.

    void setCurrentScore(int32_t value); // Dùng để cập nhật điểm số từ nơi khác trong hệ thống (ví dụ từ ngoại vi, nút bấm, UART, v.v.).
    									 //Gán giá trị value vào pendingScore và đánh dấu hasNewScore = true.
    void setHighScore(int32_t value);

    void triggerBlinkEffect();
    bool shouldStartBlinkEffect = false;
    bool shouldStopBlinkEffect = false;
protected:
    ModelListener* modelListener;  // Con trỏ ModelListener

private:
    int32_t pendingScore = 0;
    bool hasNewScore = false;

    int32_t pendingHighScore = 0;
    bool hasNewHighScore = false;


};

#endif // MODEL_HPP
