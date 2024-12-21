<div align="center">
  
# 메이플스토리 모작(WinApi, 개인 프로젝트)

<img src="https://i.namu.wiki/i/NUzo8Y8CQrxIjuZF9SlDK1ciyYMegj3PRFRi4x6qd6ll4C-jY3BEk4sPPACnrYCwWvbIZDYM49XSqT6gkBaNmg.webp" alt="이미지" width="500">

2024.01.20 ~ 2024.02.02(2주)
</div>

# 동영상
https://www.youtube.com/watch?v=KHD1HaU91bA

# 프로젝트 구현사항

### 픽셀 충돌
<img src="https://github.com/SHim719/Image/blob/main/%EB%A9%94%EC%9D%B4%ED%94%8C%EC%9D%B4%EB%8F%99.gif" alt="이미지" width="400"> <img src="https://github.com/SHim719/Image/blob/main/%ED%94%BD%EC%85%80%EC%B6%A9%EB%8F%8C%EC%9D%B4%EB%AF%B8%EC%A7%80.png" alt="이미지" width="300">

- 플레이어를 단순한 일자 지형뿐만 아니라 곡선이나 대각선 등 다양한 형태의 지형 위에 올리고 싶었습니다. 이를 구현하기 위해 픽셀 충돌 방식을 채택하는 것이 적합하다고 판단했습니다.
- 플레이어의 발 위치 픽셀 색상을 검사하여, 마젠타 색상일 경우 중력을 제거하여 지면으로 처리했습니다. 만약 마젠타가 아닌 경우, 발 아래 더 낮은 픽셀의 색상을 추가로 검사하여 노란색이라면 역시 지면으로 처리했습니다.
- 이 방식은 지형 처리뿐만 아니라, 플레이어가 로프를 탈 수 있는지 여부를 판별하거나 몬스터의 배회 경계선을 처리하는 작업 등에도 효과적으로 활용되었습니다.

### 다단히트 처리
<img src="https://github.com/SHim719/Image/blob/main/%EB%A9%94%EC%9D%B4%ED%94%8C%EB%8B%A4%EB%8B%A8%ED%9E%88%ED%8A%B81.gif" alt="이미지" width="400"> <img src="https://github.com/SHim719/Image/blob/main/%EB%A9%94%EC%9D%B4%ED%94%8C%EB%8B%A4%EB%8B%A8%ED%9E%88%ED%8A%B82.gif" alt="이미지" width="400">

- 스킬 콜라이더가 몬스터 콜라이더와 닿으면 그 몬스터 객체를 vector에 저장하고, 일정 시간마다 몬스터에게 공격판정을 주게 했습니다.
- 히트 이펙트는 동일한 위치에서만 그려지면 다이나믹한 느낌이 살지 않기때문에 몬스터 콜라이더와 스킬 콜라이더의 겹치는 영역 중심에서 랜덤 오프셋을 적용하여 히트 이펙트를 그려주었습니다.

### 카메라 보간
<img src="https://github.com/SHim719/Image/blob/main/%EC%B9%B4%EB%A9%94%EB%9D%BC%EB%B3%B4%EA%B0%842.gif" alt="이미지" width="400"> <img src="https://github.com/SHim719/Image/blob/main/%EC%B9%B4%EB%A9%94%EB%9D%BC%EB%B3%B4%EA%B0%841.gif" alt="이미지" width="400">

- 카메라가 항상 플레이어의 중심에 고정되어 있으면 어색하기 때문에, 카메라 위치와 플레이어 위치를 lerp로 보간하여 자연스럽게 플레이어를 따라다니는 느낌을 구현했습니다.


### UI

<img src="https://github.com/SHim719/Image/blob/main/%EB%A9%94%EC%9D%B4%ED%94%8CUI%EB%A0%8C%EB%8D%94%EB%A7%81.gif" alt="이미지" width="400">

- UI를 관리하는 매니져 클래스를 만들어 UI를 관리했습니다.
- UI를 관리하는 자료 구조로 list를 사용하였습니다. 마우스 입력에 따라 UI의 포커스가 변경되므로, 중간 삭제, 삽입에 용이한 list가 적합하다고 판단했습니다.
- 마우스 입력은 화면에서 가장 앞에 그려진 UI부터 처리하도록 했으며, UI 영역에서 입력을 받으면 뒤에 있는 UI는 마우스 입력을 받지 않게 했습니다.

### 미니맵

<img src="https://github.com/SHim719/Image/blob/main/%EB%AF%B8%EB%8B%88%EB%A7%B51.png" alt="이미지" width="400"> <img src="https://github.com/SHim719/Image/blob/main/%EB%AF%B8%EB%8B%88%EB%A7%B52.png" alt="이미지" width="400" height="400">


### 미니게임











