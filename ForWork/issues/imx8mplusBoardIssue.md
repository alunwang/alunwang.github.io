# U-Boot cannot recognize off-board SD/MMC
ucm-imx8m-plus=> ls mmc 1:2

Card did not respond to voltage select! : -110

刚上电时可以识别，但似乎运行一段时间，温度上升时，就不再能识别非板载SD/MMC，提示上述错误