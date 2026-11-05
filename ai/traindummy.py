
from ultralytics import YOLO
import torch

def main():
    # 1. GPU 확인
    print("CUDA 사용 가능:", torch.cuda.is_available())

    # 2. 사전학습된 YOLOv8 모델 불러오기
    model = YOLO("yolov8n.pt")

    # 3. 모델 학습
    model.train(
        data="coco8.yaml",
        epochs=10,
        imgsz=640,
        batch=4,
        device=0,
        workers=2,
        project="runs",
        name="first_train"
    )

    print("학습 완료!")

if __name__ == "__main__":
    main()

