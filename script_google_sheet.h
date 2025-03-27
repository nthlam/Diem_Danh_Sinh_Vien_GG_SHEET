function doGet(e) {
  Logger.log(JSON.stringify(e)); // Ghi log toàn bộ dữ liệu nhận từ ESP32 để kiểm tra
  var result = 'Ok'; // Kết quả mặc định trả về
  
  // Kiểm tra nếu không có tham số
  if (typeof e.parameter === 'undefined') {
    return ContentService.createTextOutput('Không có tham số');
  }

  // Thông tin Google Sheets của bạn
  var sheet_id = 'YOUR_SHEET_ID'; // Thay bằng ID Google Sheets của bạn
  var sheet_name = "DANHSACH"; // Tên sheet mặc định
  
  var sheet_open = SpreadsheetApp.openById(sheet_id);
  var sheet_target = sheet_open.getSheetByName(sheet_name);
  var newRow = sheet_target.getLastRow(); // Lấy dòng cuối cùng

  var rowDataLog = []; // Mảng lưu dữ liệu để ghi vào sheet

  // Lấy ngày và giờ hiện tại theo múi giờ Việt Nam
  var currDate = Utilities.formatDate(new Date(), "Asia/Ho_Chi_Minh", 'dd/MM/yyyy');
  rowDataLog[0] = currDate; // Ghi ngày vào cột A
  
  var currTime = Utilities.formatDate(new Date(), "Asia/Ho_Chi_Minh", 'HH:mm:ss');
  rowDataLog[1] = currTime; // Ghi giờ vào cột B

  var status = ''; // Biến lưu trạng thái từ ESP32

  // Xử lý các tham số gửi từ ESP32
  for (var param in e.parameter) {
    var value = stripQuotes(e.parameter[param]); // Lấy giá trị tham số
    Logger.log(param + ': ' + value); // Ghi log từng tham số để debug
    
    switch (param) {
      case 'sts': // Tham số trạng thái
        status = value;
        break;
      case 'uid': // Tham số UID
        rowDataLog[2] = value; // Ghi UID vào cột C
        result += ', Đã ghi UID';
        break;
      case 'name': // Tham số tên
        rowDataLog[3] = value; // Ghi tên vào cột D
        result += ', Đã ghi tên';
        break;
      case 'inout': // Tham số trạng thái vào/ra
        rowDataLog[4] = value; // Ghi vào/ra vào cột E
        result += ', Đã ghi trạng thái vào/ra';
        break;
      default:
        result += ', Tham số không hỗ trợ';
    }
  }

  // Ghi UID mới nhất nếu sts là 'writeuid'
  if (status == 'writeuid') {
    if (Array.isArray(rowDataLog) && rowDataLog.length > 2) {
      sheet_target.getRange('F1').setValue(rowDataLog[2]); // Ghi UID mới nhất vào ô F1
      return ContentService.createTextOutput('Ghi UID thành công');
    } else {
      Logger.log('Lỗi: Dữ liệu không hợp lệ');
      return ContentService.createTextOutput('Lỗi: Dữ liệu không hợp lệ');
    }
  }

  // Ghi log điểm danh nếu sts là 'writelog'
  if (status == 'writelog') {
    sheet_name = "DIEMDANH"; // Chuyển sang sheet DIEMDANH
    sheet_target = sheet_open.getSheetByName(sheet_name);
    
    sheet_target.insertRows(2); // Thêm dòng mới ở hàng 2
    var newRange = sheet_target.getRange(2, 1, 1, rowDataLog.length);
    newRange.setValues([rowDataLog]); // Ghi dữ liệu vào dòng mới
    Logger.log('Đã ghi log: ' + JSON.stringify(rowDataLog));
    return ContentService.createTextOutput('Đã ghi log điểm danh');
  }

  // Đọc dữ liệu từ sheet nếu sts là 'read'
  if (status == 'read') {
    sheet_name = "DANHSACH"; // Sheet chứa danh sách
    sheet_target = sheet_open.getSheetByName(sheet_name);
    
    var data = sheet_target.getRange('A2:C11').getDisplayValues(); // Lấy dữ liệu từ A2:C11
    return ContentService.createTextOutput(JSON.stringify(data)); // Trả dữ liệu về ESP32
  }

  return ContentService.createTextOutput(result); // Trả kết quả mặc định nếu không khớp điều kiện
}

// Xóa dữ liệu cũ trong sheet (nếu cần)
function clearOldData(maxRows) {
  var sheet = SpreadsheetApp.getActiveSpreadsheet().getSheetByName('DIEMDANH');
  sheet.getRange(maxRows + 1, 1, sheet.getLastRow() - maxRows, sheet.getLastColumn()).clearContent();
}

// Loại bỏ dấu nháy trong giá trị tham số
function stripQuotes(value) {
  return value.replace(/^["']|['"]$/g, "");
}