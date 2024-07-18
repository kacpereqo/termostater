<template>
  <div class="chart-container">sex</div>
</template>

<script setup lang="ts">
import * as echarts from 'echarts'
import { onMounted } from 'vue'

const URL = 'http://192.168.5.6:8000/reading'
const TIME_OFFSET = 3600 // 1h

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

      const xAxisData = data.map((item) => {
        // ntp time is in seconds, convert to milliseconds
        const date = new Date(item.timestamp * 1000 - TIME_OFFSET * 1000)
        return `${date.getHours()}:${date.getMinutes()}:${date.getSeconds()}`
      })
      const seriesData = data.map((item) => {
        // round to 2 decimal places
        return Math.round(item.temperature * 100) / 100
      })

      const lineChart = echarts.getInstanceByDom(
        document.querySelector('.chart-container') as HTMLElement
      )
      if (lineChart !== null && lineChart !== undefined) {
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
      }
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
      name: '°C',
      data: [999, 999],
      type: 'line'
    }
  ]
}

function onResize() {
  const lineChart = echarts.getInstanceByDom(
    document.querySelector('.chart-container') as HTMLElement
  )
  if (lineChart !== null && lineChart !== undefined) {
    lineChart.resize()
  }
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
