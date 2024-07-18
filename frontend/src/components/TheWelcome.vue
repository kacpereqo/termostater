<template>
  <div class="chart-container">sex</div>
</template>

<script setup lang="ts">
import * as echarts from 'echarts'
import { onMounted } from 'vue'

const URL = 'http://192.168.5.6:8000/reading'

interface Data {
  serial_number: string
  temperature: number
  timestamp: number
}

function fetchData() {
  fetch(URL)
    .then((response) => response.json())
    .then((data: Data[]) => {
      data = data.filter((item) => Math.abs(item.temperature) < 40)

      const xAxisData = data.map((item) => item.timestamp)
      const seriesData = data.map((item) => item.temperature)

      const lineChart = echarts.getInstanceByDom(
        document.querySelector('.chart-container') as HTMLElement
      )
      lineChart.setOption({
        xAxis: {
          data: xAxisData
        },
        series: [
          {
            data: seriesData
          }
        ]
      })
    })
    .catch((error) => {
      console.error('Error:', error)
    })
}

const lineChartOption = {
  title: {
    text: 'Line Chart'
  },
  tooltip: {
    trigger: 'axis'
  },
  legend: {
    data: ['Sales']
  },
  xAxis: {
    type: 'category',
    data: ['1', '2']
  },
  yAxis: {
    type: 'value'
  },
  series: [
    {
      name: 'Sales',
      data: [999, 999],
      type: 'line'
    }
  ]
}

function onResize() {
  const lineChart = echarts.getInstanceByDom(
    document.querySelector('.chart-container') as HTMLElement
  )
  lineChart.resize()
}

onMounted(() => {
  window.addEventListener('resize', onResize)
  const lineChart = echarts.init(document.querySelector('.chart-container') as HTMLElement)

  if (lineChart !== null) {
    fetchData()
    lineChart.setOption(lineChartOption)
  }
})
</script>

<style scoped>
.chart-container {
  width: 100vw;
  height: 100vh;
}
</style>
